import { ComponentFixture, TestBed } from '@angular/core/testing';

import { PlancheComponent } from './planche.component';

describe('PlancheComponent', () => {
  let component: PlancheComponent;
  let fixture: ComponentFixture<PlancheComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [PlancheComponent]
    })
    .compileComponents();

    fixture = TestBed.createComponent(PlancheComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
